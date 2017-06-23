<?php

$servername = "localhost";
$username = "root";

try{
	$dbConnect = new PDO("mysql:host=$servername;dbname=elevator", $username, '');
	$dbConnect->setAttribute(PDO::ATTR_DEFAULT_FETCH_MODE, PDO::FETCH_ASSOC);
}
catch(PDOException $e){
	echo "Connection failed: " . $e->getMessage();
}

$rows = $dbConnect->query('SELECT * FROM elevatorNetwork ORDER BY nodeID');

foreach ($rows as $row){
	echo $row['date'];
	echo "<br/>";
}
?>



