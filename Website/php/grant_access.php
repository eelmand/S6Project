<?php
	// Get user info from Javascript
	$username = $_POST["username"];
	echo $username;

	include "connect_db.php";		// Connect to the remote database

	// Query for first name, last name and password based on 
	$rows = $database->query("SELECT username, password first_name, last_name FROM new_users WHERE username='" .
			$username . "' DESC LIMIT 1");

	if($rows != FALSE) {
		foreach($rows as $row){
			$username = $row['username'];
			$password = $row['password'];
			$first_name = $row['first_name'];
			$last_name = $row['last_name'];
		}
	}
	else {
		echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
		exit();
	}

	echo 'here';
	echo $password;

	// Prep a query for inputting into the database
	$query = 'INSERT INTO new_users(username, password, first_name, last_name) VALUES(:username, :password, :first_name, :last_name)';
	$statement = $database->prepare($query);
	
	$params = [
		'username' => $username,
		'password' => $password,
		'first_name' => $first_name,
		'last_name' => $last_name
	];

	// Execute the query
	$result = $statement->execute($params);

	// Delete user from new_users table
	$database->query("DELETE FROM new_users WHERE username='" . $username . "'");
?>