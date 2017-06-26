<?php

$servername = "localhost";
$username = "root";

echo "<script type='text/javascript'> console.log('CONNECTING TO DATABASE') </script>";

try{
	$dbConnect = new PDO("mysql:host=$servername;dbname=elevator", $username, '');
	$dbConnect->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
}
catch(PDOException $e){
	echo "Connection failed: " . $e->getMessage();
}

echo "<script type='text/javascript'> console.log('CONNECTED TO DATABASE') </script>";

$rows = $dbConnect->query('SELECT * FROM elevatorNetwork ORDER BY nodeID');

foreach ($rows as $row){
	echo $row['date'];
	echo "<br/>";
}
?>