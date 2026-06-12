from cs50 import SQL
from flask import Flask, render_template, redirect, request

app = Flask(__name__)
db = SQL("sqlite:///froshims.db")

SPORTS = ["Basketball", "Soccer", "Ultimate Frisbee"]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTS)

@app.route("/deregister", methods=["POST"])
def deregister():
    id = request.form.get("id")
    if id:
        db.execute("DELECT FROM registrants WHERE id = ?", id)
    return redirect("/registrants")

@app.route("/register", methods=["POST"])
def register():
    name = request.form.get("name")
    if not name:
        return render_template("error.html", message="Missing Name")

    sports = request.form.getlist("sport")
    if not sports:
        return render_template("error.html", message="Missing Sports")
    for sport in sports:
        if sport not in SPORTS:
            return render_template("error.html", message="Invalid Sport")

    for sport in sports:
        db.execute("INSERT INTO registrans (name, sport) VALUES(?, ?)", name, sport)

    return redirect("/registrants")

@app.route("/registrants")
def registrants():
    registrants = db.execute("SELECT * FROM registrants")
    return render_template("registrants.html", registrants=registrants)
