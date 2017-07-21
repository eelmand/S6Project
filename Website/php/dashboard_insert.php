<?php
	include "connect_db.php";		// Connect to the remote database
	
	// Prep a query for inputting into the database
	$query = 'INSERT INTO signals (name, timestamp, raw, phys) VALUES(:name, :thing, :raw, :phys)';
	$statement = $database->prepare($query);
	
	// Collect data for the database
	$floorRequested = $_POST['floorRequested'];
	$date = date('Y-m-d H:i:s');

	$params = [
		'name' => 'REMOTE_REQ',
		'thing' => $date,
		'raw' => $floorRequested,
		'phys' => 'Floor ' . $floorRequested
	];

	// Execute the query
	$result = $statement->execute($params);
	echo $result;
?>