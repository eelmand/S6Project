<?php
	session_start();	// starts a session and creates a session variable

	$username = $_POST["username"];		// get username
	$password  = $_POST["password"];	// get password
	$remember = isset($_POST["remember"]);		// get rememberMe 

	include "connect_db.php";		// Connect to the remote database

	//check if the username entered is in the database.
	$login_query = "SELECT * FROM users WHERE username = '".$username."'";
	$query_result = $database->query($login_query);

	//conditions
	if($query_result != FALSE) {
		foreach($query_result as $row_query) {
			// check if password are equal
	        if($row_query['password']==$password)
	        {
	        	/*
				// remember username & password to session if "Remember me" was set
				*/
	            $_SESSION["username"] = $username;
				$_SESSION["password"] = $password; 

				// Update last login time for this user
				$timestamp_query = "UPDATE users SET last_login=NOW() WHERE username='" . $username ."'";
				$query_result = $database->query($timestamp_query);
				// Not checking result for now

	            header("Location: ../dashboard.html"); /* Redirect browser */
	        }
	        else
			{
				echo "<strong>Invalid login info</strong>";
				header("Location: ../login.html"); /* Redirect browser */
			}
		}


	}
	else {
		echo "<strong>Invalid login info</strong>";
		header("Location: ../login.html"); /* Redirect browser */
	}

?>