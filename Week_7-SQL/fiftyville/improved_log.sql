--* Main query that identifies main suspect, the thief, and the city they escaped to.
SELECT people.*
  FROM people

  JOIN -- People that withdrawed on Leggett Street on day of theft.
       (SELECT bank.*
          FROM bank_accounts
               AS bank
          JOIN atm_transactions
               AS atm
            ON bank.account_number = atm.account_number
         WHERE atm.month = 7
           AND atm.day = 28
           AND atm.year = 2024
           AND atm.transaction_type = 'withdraw'
           AND atm.atm_location = 'Leggett Street')
               AS sus_bank_account
    ON people.id = sus_bank_account.person_id

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
               AS sus_passenger
    ON people.id = sus_passenger.id

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
       (SELECT people.*
          FROM people
          JOIN phone_calls
            ON people.phone_number = phone_calls.caller
         WHERE phone_calls.month = 7
           AND phone_calls.day = 28
           AND phone_calls.year = 2024
           AND phone_calls.duration <= 60)
               AS sus_call
    ON people.id = sus_call.id;






--* Query to get accomplice of thief
-- SELECT people.*
--   FROM people
--   JOIN
--        (SELECT people.*,
--                sus_call.receiver
--                AS called
--           FROM people
--           JOIN -- People that withdrawed on Leggett Street on day of theft.
--                (SELECT people.*
--                   FROM people
--                   JOIN
--                        (SELECT bank.*
--                           FROM bank_accounts
--                                AS bank
--                           JOIN
--                                (SELECT *
--                                   FROM atm_transactions
--                                  WHERE month = 7
--                                    AND day = 28
--                                    AND year = 2024
--                                    AND transaction_type = 'withdraw'
--                                    AND atm_location = 'Leggett Street')
--                                        AS sus_atm
--                             ON bank.account_number = sus_atm.account_number)
--                                AS sus_bank  
--                     ON people.id = sus_bank.person_id)
--                        AS sus_people_atm
--             ON people.id = sus_people_atm.id
--           JOIN -- Passengers on board the earliest flight next day after theft.
--                (SELECT people.*
--                   FROM people
--                   JOIN passengers
--                     ON people.passport_number = passengers.passport_number
--                   JOIN
--                        (SELECT flights.*
--                           FROM flights
--                           JOIN airports
--                                AS origin_airport
--                             ON flights.origin_airport_id = origin_airport.id
--                           JOIN airports
--                                AS destination_airport
--                             ON flights.destination_airport_id = destination_airport.id
--                          WHERE flights.month = 7
--                            AND flights.day = 29
--                            AND flights.year = 2024
--                            AND origin_airport.city = 'Fiftyville'
--                          ORDER BY flights.hour
--                          LIMIT 1)
--                                AS sus_flight
--                     ON passengers.flight_id = sus_flight.id)
--                        AS sus_passengers
--             ON people.id = sus_passengers.id
--           JOIN -- People that exit parking lot within 10 mins after theft.
--                (SELECT people.*
--                   FROM bakery_security_logs
--                        AS parking_logs
--                   JOIN people
--                     ON people.license_plate = parking_logs.license_plate
--                  WHERE parking_logs.month = 7
--                    AND parking_logs.day = 28
--                    AND parking_logs.year = 2024
--                    AND parking_logs.activity = 'exit'
--                    AND parking_logs.hour = 10
--                    AND parking_logs.minute 
--                        BETWEEN 15 AND 25
--                  ORDER BY parking_logs.minute)
--                           AS sus_car
--             ON people.id = sus_car.id
--           JOIN -- Phone calls on day of theft with duration less than a minute.
--                (SELECT people.*,
--                        phone_calls.receiver
--                   FROM people
--                   JOIN phone_calls
--                     ON people.phone_number = phone_calls.caller
--                  WHERE phone_calls.month = 7
--                    AND phone_calls.day = 28
--                    AND phone_calls.year = 2024
--                    AND phone_calls.duration <= 60
--                  ORDER BY phone_calls.duration)
--                           AS sus_call
--             ON people.id = sus_call.id)
--                AS thief
--  WHERE people.phone_number = thief.called;