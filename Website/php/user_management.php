<?php
	// Get user info from Javascript
	$username = $_POST["username"];
	echo $username;

	include "connect_db.php";		// Connect to the remote database

	// Check if this is a grant access or revoke access request
	if (isset($_POST['grant_access'])) {
		// Query for first name, last name and password based on 
		$rows = $database->query("SELECT username, password, first_name, last_name, email, last_login FROM new_users WHERE username='" .
				$username . "' LIMIT 1");
		while($record = $db->fetch_array($rows)) {
			if($record['rcount'] == 0) {
				echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
				exit();	
			}
			else {
				foreach($rows as $row){
					$username = $row['username'];
					$password = $row['password'];
					$first_name = $row['first_name'];
					$last_name = $row['last_name'];
					$email = $row['email'];
					$last_login = $row['last_login'];
				}	
			}
		}

		// Prep a query for inputting into the database
		$query = 'INSERT INTO users(username, password, first_name, last_name, email, last_login) VALUES(:username, :password, :first_name, :last_name, :email, :last_login)';
		$statement = $database->prepare($query);
		
		$params = [
			'username' => $username,
			'password' => $password,
			'first_name' => $first_name,
			'last_name' => $last_name,
			'email' => $email,
			'last_login' => $last_login
		];

		// Execute the query
		$result = $statement->execute($params);

		// Delete user from new_users table
		$database->query("DELETE FROM new_users WHERE username='" . $username . "'");
	} else if (isset($_POST['revoke_access'])) {
	    // Simple delete query
	    $database->query("DELETE FROM users WHERE username='" . $username . "'");
	}

	// Redirect back to user_management.html
	header("Location: ../user_management.html"); /* Redirect browser */
?>