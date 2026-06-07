-- 8. Names of people who starred in Toy Story
SELECT name
FROM people, stars, movies
WHERE people.id = stars.person_id
AND stars.movie_id = movies.id
AND movies.title = "Toy Story";
