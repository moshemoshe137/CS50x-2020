-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Look for a record of the crime
SELECT description FROM crime_scene_reports WHERE month = 7 AND day = 28 AND year = 2020 AND street = "Chamberlin Street";


-- Inerview Transcripts mention courthouse... idk what that means...
-- But, let's look at courthouse_security_logs
-- Let's try day-of

SELECT activity, license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020;

-- Doesn't look too helpful... Maybe I can count the plates?

SELECT license_plate, COUNT(license_plate) FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 GROUP BY license_plate;

-- Nothing there...

-- Ope! I'm so dumb! There's a interviews table! Note to self: Read the WHOLE list of tables

SELECT * FROM interviews WHERE month = 7 AND day = 28 AND year = 2020;

-- Mr. Windibank is nameddropped, and is annoyed... From France
-- Someone sketchy has a german accent? "Said he would call" Barbara?
-- Look for cars who left around 10 min after the crime
-- Theif called and said he would take earliest flight tomorrow

-- Scrolled up to see theft took place at 10:15 am. Who left courthouse around then?

SELECT * FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25;

-- Can I find the owners of these cars?

SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25);

-- Got some suspects! Did any of them fly?

SELECT * FROM passengers WHERE passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25));

-- I can do better than that query, I hope...

SELECT * FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
WHERE people.passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25));

-- This is nice and all, but I need to know what dates all these flights took place...

SELECT * FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE people.passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25))
AND year=2020 AND month = 7 AND day = 29;

-- Wow, seriously? That's a surprising number of matches... However, it's probably not Russell on the late flight...

SELECT * FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE people.passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25))
AND year=2020 AND month = 7 AND day = 29 AND hour < 12;

-- Did of these people make a < 1 min phone call on the morning of the crime?

SELECT people.id from people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE duration < 60
AND phone_calls.caller IN
(SELECT phone_number FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE people.passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25))
AND year=2020 AND month = 7 AND day = 29 AND hour < 12);

-- Okay, Danielle looks innocent...
-- Welp, I guess I'll check who was ATMing...
-- But first, it seems I need account numbers...

SELECT * FROM bank_accounts
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
JOIN people ON bank_accounts.person_id = people.id
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street"
AND person_id IN
(SELECT people.id from people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE duration < 60
AND phone_calls.caller IN
(SELECT phone_number FROM people
JOIN passengers ON people.passport_number = passengers.passport_number
JOIN flights ON passengers.flight_id = flights.id
WHERE people.passport_number IN (SELECT passport_number FROM people WHERE license_plate IN (SELECT license_plate FROM courthouse_security_logs WHERE month = 7 AND day = 28 AND year = 2020 AND hour = 10 AND minute >=15 AND minute <=25))
AND year=2020 AND month = 7 AND day = 29 AND hour < 12));

-- OMG, IT'S ERNEST

-- Where did Ernest Fly?

SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name = "Ernest");

SELECT destination_airport_id FROM flights WHERE id = (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name = "Ernest"));

SELECT full_name, city FROM airports WHERE id = (SELECT destination_airport_id FROM flights WHERE id = (SELECT flight_id FROM passengers WHERE passport_number = (SELECT passport_number FROM people WHERE name = "Ernest")));


-- AHA! London!


-- who did he call?
SELECT phone_number FROM people WHERE name = "Ernest";

SELECT * FROM people WHERE phone_number =
(SELECT receiver FROM phone_calls 
WHERE duration < 60 AND day = 28
AND caller IN (SELECT phone_number FROM people WHERE name = "Ernest"));
