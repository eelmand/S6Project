<?php

	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=127.0.0.1;dbname=elevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		echo "Error: " . $e->getMessage() . "<br />";
		return;
	}

	// Query database for all user info in new_users table
	$data = array();

	$rows = $database->query("SELECT username, password, first_name, last_name FROM new_users");

	if($rows != FALSE) {
		foreach($rows as $row){
			$new_row = array('username'=>$row['username'], 'first_name'=>$row['first_name'], 'last_name'=>$row['last_name']);
			array_push($data, $new_row);
		}
	}
	else {
		//echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
	}

	// Encode data into JSON for easy Javascript passing & parsing
	$json_data = json_encode($data);
	echo $json_data;
?>