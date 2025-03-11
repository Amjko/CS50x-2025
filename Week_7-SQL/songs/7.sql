SELECT AVG(songs.energy) AS 'avg energy of Drake' FROM songs
 JOIN artists ON songs.artist_id = artists.id
  WHERE artists.name = 'Drake';
