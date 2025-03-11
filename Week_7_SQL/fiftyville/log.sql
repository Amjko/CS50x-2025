-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Select the information with the date: 7/28/2024
/*
    SELECT *
      FROM crime_scene_reports
     WHERE month = 7
       AND day = 28
       AND year = 2024;
*/

/*
  Significant information from crime scene reports:
  1. Theft took at 10:15am.
  2. Interviews conducted with 3 witnesses.
  3. Interviewees mentioned the bakery.
*/

-- Information from interviewed witnesses on 7/28/2024
/*
    SELECT *
      FROM interviews
     WHERE month = 7
       AND day = 28
       AND year = 2024;
*/

/*
  * WITNESSES *
  Significant information from witnesses:
  1. Before Eugene arrived at Emma's bakery, he saw the thief withdrawing
     money from the ATM on Leggett Street.
  2. Ruth saw thief get into a car in the parking lot of the bakery within
     ten minutes of the theft.
     NOTE: LOOK FOR CARS LEAVING 10:25am - 10:30am
  3. Raymond saw thief talking to someone in a call for less than a minute
     as the thief was leaving the bakery.
  4. The thief and accomplice planned to leave the town via earliest flight
     the next day.
     NOTE: LOOK FOR EARLIEST LEAVING PLANE ON 7/29/2024
*/

-- Information from flight logs on 7/29/2024
/*
    SELECT * 
      FROM flights
     WHERE month = 7
       AND day = 29
       AND year = 2024;
*/

/*
  * FLIGHT LOGS *
  Significant information from flight logs:
  1. Earliest flight: 8:20am
     - Destination id: 4
     - Origin airport id: 8
*/

-- Plane information format: FLIGHT_ID/ORIGIN_AIRPORT_ID/DESTINATION_ID/HOUR/MINUTE
-- Information of passengers on 36/8/4/8/20
/*
    SELECT passport_number, seat
      FROM passengers
     WHERE flight_id = 36;
*/

/*
  * FLIGHT PASSENGERS *
  Significant information from passengers on flight 36/8/4/8/20
  +------------+------+
  | passport   | seat |
  +------------+------+
  | 7214083635 | 2A   |
  | 1695452385 | 3B   |
  | 5773159633 | 4A   |
  | 1540955065 | 5C   |
  | 8294398571 | 6C   |
  | 1988161715 | 6D   |
  | 9878712108 | 7A   |
  | 8496433585 | 7B   |
  +------------+------+
*/

-- Information from ATM transactions on 7/28/2024 Leggett Street
/*
    SELECT *
      FROM atm_transactions
     WHERE month = 7
       AND day = 28
       AND year = 2024
        AND atm_location = 'Leggett Street';
*/

-- Information from airports related to flight logs
/*
    SELECT *
      FROM airports
     WHERE id = 8
        OR id = 4;
*/

/*
  * AIRPORTS *
  Significant information of destination and origin airports
  +----+-----+-----------------------------+---------------+
  | id | abr |          full_name          |     city      |
  +----+-----+-----------------------------+---------------+
  | 4  | LGA | LaGuardia Airport           | New York City |
  | 8  | CSF | Fiftyville Regional Airport | Fiftyville    |
  +----+-----+-----------------------------+---------------+
*/

/*
  * WITHDRAWS *
  Significant information from withdraws on 7/28/2024 Leggett Street
  +-----+----------+------+---+-----+---------------+----------+----+
  | id  | account  | y    | m | d  |  atm_location  | type     | amt|
  +-----+----------+------+---+----+----------------+----------+----+
  | 246 | 28500762 | 2024 | 7 | 28 | Leggett Street | withdraw | 48 |
  | 264 | 28296815 | 2024 | 7 | 28 | Leggett Street | withdraw | 20 |
  | 266 | 76054385 | 2024 | 7 | 28 | Leggett Street | withdraw | 60 |
  | 267 | 49610011 | 2024 | 7 | 28 | Leggett Street | withdraw | 50 |
  | 269 | 16153065 | 2024 | 7 | 28 | Leggett Street | withdraw | 80 |
  | 288 | 25506511 | 2024 | 7 | 28 | Leggett Street | withdraw | 20 |
  | 313 | 81061156 | 2024 | 7 | 28 | Leggett Street | withdraw | 30 |
  | 336 | 26013199 | 2024 | 7 | 28 | Leggett Street | withdraw | 35 |
  +-----+----------+------+---+----+----------------+----------+----+
*/

-- Information from bank accounts related to withdraws information
/*
    SELECT *
      FROM bank_accounts
     WHERE account_number IN
          (28500762, 28296815, 76054385, 49610011,
           16153065, 25506511, 81061156, 26013199);
*/

/*
  * BANK ACCOUNTS *
  Significant information from bank accounts
  +----------+--------+------+
  | account  | person | year |
  +----------+--------+------+
  | 49610011 | 686048 | 2010 |
  | 26013199 | 514354 | 2012 |
  | 16153065 | 458378 | 2012 |
  | 28296815 | 395717 | 2014 |
  | 25506511 | 396669 | 2014 |
  | 28500762 | 467400 | 2014 |
  | 76054385 | 449774 | 2015 |
  | 81061156 | 438727 | 2018 |
  +----------+--------+------+
*/

-- Information from bakery security logs on 7/28/2024
/*
    SELECT *
      FROM bakery_security_logs
     WHERE month = 7
       AND day = 28
       AND year = 2024
       AND hour = 10;
*/

/*
  * PARKING LOGS *
  Significant information from bakery parking logs minutes after theft
  +-----+------+---+----+----+----+------+---------+
  | id  | y    | m | d  | h  | m  | act  | license |
  +-----+------+---+----+----+----+------+---------+
  | 260 | 2024 | 7 | 28 | 10 | 16 | exit | 5P2BI95 |
  | 261 | 2024 | 7 | 28 | 10 | 18 | exit | 94KL13X |
  | 262 | 2024 | 7 | 28 | 10 | 18 | exit | 6P58WS2 |
  | 263 | 2024 | 7 | 28 | 10 | 19 | exit | 4328GD8 |
  | 264 | 2024 | 7 | 28 | 10 | 20 | exit | G412CB7 |
  | 265 | 2024 | 7 | 28 | 10 | 21 | exit | L93JTIZ |
  | 266 | 2024 | 7 | 28 | 10 | 23 | exit | 322W7JE |
  | 267 | 2024 | 7 | 28 | 10 | 23 | exit | 0NTHK55 |
  | 268 | 2024 | 7 | 28 | 10 | 35 | exit | 1106N58 |
  +-----+------+---+----+----+----+------+---------+
*/

-- Final query that identifies thief, accomplice, and the city they escaped to

/*
  CONNECTED TABLES
  
  - ATM_TRANSACTIONS
    account_number

  - BANK_ACCOUNTS
    person_id
    account_number

  - FLIGHTS
    id
    airport_id

  - AIRPORTS
    id

  - PASSENGERS
    flight_id

  - PEOPLE
    id
    phone_number

  - PHONE_CALLS
    caller/text

  - BAKERY_SECURITY_LOGS
    license_plate
*/

--* Main query that identifies main suspect, the thief, and the city they escaped to.
SELECT people.*,                       -- Personal information of thief
       sus_call.receiver,              -- Who thief called
       sus_call.call_duration,         -- Call duration with thief
       sus_car.parking_activity,       -- Thief exit parking
       sus_car.hour,                   -- Time (hour) thief exit parking
       sus_car.minute,                 -- Time (minute) thief exit parking
       sus_passengers.origin_city,     -- Airport thief took
       sus_passengers.destination_city -- Airport thief landed
  FROM people
  JOIN -- People that withdrawed on Leggett Street on day of theft.
       (SELECT people.*
          FROM people
          JOIN
               (SELECT bank.*
                  FROM bank_accounts
                       AS bank
                  JOIN
                       (SELECT *
                          FROM atm_transactions
                         WHERE month = 7
                           AND day = 28
                           AND year = 2024
                           AND transaction_type = 'withdraw'
                           AND atm_location = 'Leggett Street')
                               AS sus_atm
                    ON bank.account_number = sus_atm.account_number)
                       AS sus_bank  
            ON people.id = sus_bank.person_id)
               AS sus_people_atm
    ON people.id = sus_people_atm.id
  JOIN -- Passengers on board the earliest flight next day after theft.
       (SELECT people.*,
               sus_flight.origin_city,
               sus_flight.destination_city
          FROM people
          JOIN passengers
            ON people.passport_number = passengers.passport_number
          JOIN
               (SELECT flights.*,
                       origin_airport.city
                       AS origin_city,
                       destination_airport.city
                       AS destination_city
                  FROM flights
                  JOIN airports
                       AS origin_airport
                    ON flights.origin_airport_id = origin_airport.id
                  JOIN airports
                       AS destination_airport
                    ON flights.destination_airport_id = destination_airport.id
                 WHERE flights.month = 7
                   AND flights.day = 29
                   AND flights.year = 2024
                   AND origin_airport.city = 'Fiftyville'
                 ORDER BY flights.hour
                 LIMIT 1)
                       AS sus_flight
            ON passengers.flight_id = sus_flight.id)
               AS sus_passengers
    ON people.id = sus_passengers.id
  JOIN -- People that exit parking lot within 10 mins after theft.
       (SELECT people.*,
               parking_logs.hour,
               parking_logs.minute,
               parking_logs.activity
               AS parking_activity
          FROM bakery_security_logs
               AS parking_logs
          JOIN people
            ON people.license_plate = parking_logs.license_plate
         WHERE parking_logs.month = 7
           AND parking_logs.day = 28
           AND parking_logs.year = 2024
           AND parking_logs.activity = 'exit'
           AND parking_logs.hour = 10
           AND parking_logs.minute 
               BETWEEN 15 AND 25
         ORDER BY parking_logs.minute)
               AS sus_car
    ON people.id = sus_car.id
  JOIN -- Phone calls on day of theft with duration less than a minute.
       (SELECT people.*,
               phone_calls.receiver,
               phone_calls.duration
               AS call_duration
          FROM people
          JOIN phone_calls
            ON people.phone_number = phone_calls.caller
         WHERE phone_calls.month = 7
           AND phone_calls.day = 28
           AND phone_calls.year = 2024
           AND phone_calls.duration <= 60
         ORDER BY phone_calls.duration)
               AS sus_call
    ON people.id = sus_call.id;

--* Query to get accomplice of thief
SELECT people.*
  FROM people
  JOIN
       (SELECT people.*,
               sus_call.receiver
               AS called
          FROM people
          JOIN -- People that withdrawed on Leggett Street on day of theft.
               (SELECT people.*
                  FROM people
                  JOIN
                       (SELECT bank.*
                          FROM bank_accounts
                               AS bank
                          JOIN
                               (SELECT *
                                  FROM atm_transactions
                                 WHERE month = 7
                                   AND day = 28
                                   AND year = 2024
                                   AND transaction_type = 'withdraw'
                                   AND atm_location = 'Leggett Street')
                                       AS sus_atm
                            ON bank.account_number = sus_atm.account_number)
                               AS sus_bank  
                    ON people.id = sus_bank.person_id)
                       AS sus_people_atm
            ON people.id = sus_people_atm.id
          JOIN -- Passengers on board the earliest flight next day after theft.
               (SELECT people.*
                  FROM people
                  JOIN passengers
                    ON people.passport_number = passengers.passport_number
                  JOIN
                       (SELECT flights.*
                          FROM flights
                          JOIN airports
                               AS origin_airport
                            ON flights.origin_airport_id = origin_airport.id
                          JOIN airports
                               AS destination_airport
                            ON flights.destination_airport_id = destination_airport.id
                         WHERE flights.month = 7
                           AND flights.day = 29
                           AND flights.year = 2024
                           AND origin_airport.city = 'Fiftyville'
                         ORDER BY flights.hour
                         LIMIT 1)
                               AS sus_flight
                    ON passengers.flight_id = sus_flight.id)
                       AS sus_passengers
            ON people.id = sus_passengers.id
          JOIN -- People that exit parking lot within 10 mins after theft.
               (SELECT people.*
                  FROM bakery_security_logs
                       AS parking_logs
                  JOIN people
                    ON people.license_plate = parking_logs.license_plate
                 WHERE parking_logs.month = 7
                   AND parking_logs.day = 28
                   AND parking_logs.year = 2024
                   AND parking_logs.activity = 'exit'
                   AND parking_logs.hour = 10
                   AND parking_logs.minute 
                       BETWEEN 15 AND 25
                 ORDER BY parking_logs.minute)
                          AS sus_car
            ON people.id = sus_car.id
          JOIN -- Phone calls on day of theft with duration less than a minute.
               (SELECT people.*,
                       phone_calls.receiver
                  FROM people
                  JOIN phone_calls
                    ON people.phone_number = phone_calls.caller
                 WHERE phone_calls.month = 7
                   AND phone_calls.day = 28
                   AND phone_calls.year = 2024
                   AND phone_calls.duration <= 60
                 ORDER BY phone_calls.duration)
                          AS sus_call
            ON people.id = sus_call.id)
               AS thief
 WHERE people.phone_number = thief.called;