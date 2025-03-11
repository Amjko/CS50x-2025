SELECT name FROM (
    SELECT songs.name, artists.name FROM songs
    JOIN artists ON songs.artist_id = artists.id
    WHERE artists.name = 'Post Malone'
);