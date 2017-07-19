<?php
	$username = $_POST["username"];

	// Get user info from Javascript
	$username = $_POST["username"];
	$password  = $_POST["password"];
	$first_name = $_POST["first_name"];
	$last_name = $_POST["last_name"];

	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=127.0.0.1;dbname=elevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		//echo "Error: " . $e->getMessage() . "<br />";
		return;
	}

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