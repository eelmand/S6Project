<?php
	$username = $_POST["username"];

	// Get user info from Javascript
	$username = $_POST["username"];
	$password  = $_POST["password"];
	$first_name = $_POST["first_name"];
	$last_name = $_POST["last_name"];

	include "connect_db.php";		// Connect to the remote database

	// Prep a query for inputting into the database
	$query = 'INSERT INTO new_users (username, password, first_name, last_name) VALUES(:username, :password, :first_name, :last_name)';
	$statement = $database->prepare($query);
	
	$params = [
		'username' => $username,
		'password' => $password,
		'first_name' => $first_name,
		'last_name' => $last_name
	];

	// Execute the query
	$result = $statement->execute($params);
?>