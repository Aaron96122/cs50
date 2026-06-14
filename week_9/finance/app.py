import os

from cs50 import SQL
import datetime
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    table = []
    user_id = session["user_id"]
    cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    rows = db.execute(
        "SELECT symbol, name, SUM(shares), SUM(shares * price) FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)
    for row in rows:
        temp = {}
        temp["symbol"] = row["symbol"]
        temp["name"] = row["name"]
        temp["shares"] = row["SUM(shares)"]
        temp["total_value"] = row["SUM(shares * price)"]
        temp["current_price"] = lookup(row["symbol"])["price"]
        temp["grand_value"] = cash[0]["cash"] + row["SUM(shares * price)"]
        table.append(temp)

    return render_template("/index.html", user_id=user_id, cash=cash[0]["cash"], table=table)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("/buy.html")
    else:
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
    if not symbol:
        return apology("Missing symbol")
    if not quote:
        return apology("Invalid symbol")

    try:
        shares = int(request.form.get("shares"))
        if not shares or shares <= 0:
            raise ValueError
    except ValueError:
        return apology("Please type in a correct number of shares")

    row = db.execute("SELECT * FROM users WHERE id = ?", session["user_id"])
    cash = row[0]["cash"] - shares * quote["price"]
    if cash < 0:
        return apology("You cannot afford to buy this amount of stock at this price")
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
    db.execute("INSERT INTO transactions (user_id, symbol, shares, name, price, timestamp) VALUES (?, ?, ?, ?, ?, ?)",
               session["user_id"],
               symbol,
               shares,
               quote["name"],
               quote["price"],
               datetime.datetime.now())
    return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    account = db.execute("SELECT * FROM transactions WHERE user_id = ?", user_id)
    table = []
    for row in account:
        temp = {}
        temp["symbol"] = row["symbol"]
        if row["shares"] > 0:
            temp["label"] = "Bought"
        else:
            temp["label"] = "Sold"
        temp["shares"] = row["shares"]
        temp["price"] = row["price"]
        temp["date"] = row["timestamp"].split(" ")[0]
        temp["time"] = row["timestamp"].split(" ")[1]
        table.append(temp)
    return render_template("/history.html", table=table)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""
    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if not symbol or not quote:
            return apology("Please type in a correct symbol of some stock")
        return render_template("/quoted.html", quote=quote)
    else:
        return render_template("/quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")
        if not name or not password or not confirmation:
            return apology("please provide username and/or password with confirmation")
        if password != confirmation:
            return apology("passwords do not match")
        try:
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)",
                       name, generate_password_hash(password))
            return redirect("/")
        except ValueError:
            return apology("username already existed")
    else:
        return render_template("/register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]
    if request.method == "GET":
        symbols = db.execute(
            "SELECT symbol FROM transactions WHERE user_id =? GROUP BY symbol", user_id)
        return render_template("/sell.html", symbols=symbols)
    else:
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        if not shares:
            return apology("Invalid shares")
        shares = int(shares)
        if shares <= 0:
            return apology("Invalid symbol or shares")

        account = db.execute("SELECT symbol, name, SUM(shares) as sumshares FROM transactions WHERE user_id = ? AND symbol = ?",
                             user_id, symbol)
        if shares > account[0]["sumshares"]:
            return apology("You do not own any shares of this stock")

        price = lookup(symbol)["price"]
        db.execute(
            "INSERT INTO transactions (user_id, symbol, shares, name, price, timestamp) VALUES(?, ?, ?, ?, ?, ?)",
            user_id, symbol, -shares, account[0]["name"], price, datetime.datetime.now()
        )
        gain = shares * price
        row = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = row[0]["cash"] + gain
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, user_id)
        return redirect("/")
