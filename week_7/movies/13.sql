-- 13. Names of all people who starred in a movie in which Kevin Bacon also starred
SELECT name
FROM people
WHERE id
IN (
    SELECT distinct(person_id)
    FROM stars
    WHERE movie_id
    IN (
        SELECT movie_id
        FROM stars, people
        WHERE stars.person_id = people.id
        AND people.name = "Kevin Bacon"
        AND people.birth = 1958
        )
    )
AND name != "Kevin Bacon";
