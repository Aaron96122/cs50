-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT * FROM crime_scene_reports WHERE description LIKE "%theft%" AND description LIKE "%duck%";
-- By doing this, we get the information from the description of "Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery."
-- In this context, we need to check the interview transcripts at the same date;
SELECT transcript FROM interviews, crime_scene_reports WHERE interviews.year = crime_scene_reports.year AND interviews.month = crime_scene_reports.month AND interviews.day = crime_scene_reports.day AND interviews.transcript LIKE "%bakery%" AND crime_scene_reports.description LIKE "%theft%" AND crime_scene_reports.description LIKE "%duck%";
-- Thus, we get three pieces of useful information as follows:
-- 1. As the thief was leaving the bakery, they called someone who talked to them for less than a minute. In the call, I heard the thief say that they were planning to take the earliest flight out of Fiftyville tomorrow. The thief then asked the person on the other end of the phone to purchase the flight ticket.
SELECT caller FROM phone_calls AS caller_theft WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60;
SELECT receiver FROM phone_calls AS receiver_accomplice WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60;
SELECT passport_number FROM passengers AS passports WHERE flight_id IN (SELECT flights.id FROM flights JOIN airports ON flights.origin_airport_id = airports.id AND airports.city = "Fiftyville" AND year = 2025 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1);

-- The intersection between caller_theft and found passport
SELECT id FROM people WHERE phone_number IN (
    SELECT caller FROM phone_calls AS caller_theft WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60)
    AND passport_number IN (
    SELECT passport_number FROM passengers AS passports WHERE flight_id IN (SELECT flights.id FROM flights JOIN airports ON flights.origin_airport_id = airports.id AND airports.city = "Fiftyville" AND year = 2025 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1)
    );
-- Similarly, the intersection between receiver_accomplice and found passport
SELECT * FROM people WHERE phone_number IN (
   SELECT receiver FROM phone_calls AS receiver_accomplice WHERE year = 2025 AND month = 7 AND day = 28 AND duration < 60)
   AND passport_number IN (
   SELECT passport_number FROM passengers AS passports WHERE flight_id IN (SELECT flights.id FROM flights JOIN airports ON flights.origin_airport_id = airports.id AND airports.city = "Fiftyville" AND year = 2025 AND month = 7 AND day = 29 ORDER BY hour LIMIT 1)
   );
-- here we get the name of the accomplice : 953679 | Doris | (066) 555-9701 | 7214083635      | M51FA04

-- 2. I don't know the thief's name, but it was someone I recognized. Earlier this morning, before I arrived at Emma's bakery, I was walking by the ATM on Leggett Street and saw the thief there withdrawing some money.
SELECT account_number FROM atm_transactions WHERE year = 2025 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw";
SELECT id FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE year = 2025 AND month = 7 AND day = 28 AND atm_location = "Leggett Street" AND transaction_type = "withdraw");
-- 3. Sometime within ten minutes of the theft, I saw the thief get into a car in the bakery parking lot and drive away. If you have security footage from the bakery parking lot, you might want to look for cars that left the parking lot in that time frame.
SELECT license_plate FROM bakery_security_logs WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 35 AND activity = "exit";
SELECT id FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE year = 2025 AND month = 7 AND day = 28 AND hour = 10 AND minute < 35 AND activity = "exit");
-- Through intersecting the three conditions we get the final id of the theft Bruce
