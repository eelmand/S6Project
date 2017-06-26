<?php

//include "admin_info.php"; // include Admin Login Info 

session_start();	// starts a session and creates a session variable

$username = $_POST["username"];		// get username
$password  = $_POST["password"];	// get password
$remember = isset($_POST["remember"]);		// get rememberMe 


// check if login info is valid
if(!($username&&$password))			
{
	echo "<strong>Please fill username and password fields!</strong>";
	header("Location: ../login.html"); /* Redirect browser */
	exit();
}
else
{
	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=127.0.0.1;dbname=elevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		echo "Error: " . $e->getMessage() . "<br />";
	}

	//check if the username entered is in the database.
	$login_query = "SELECT * FROM users WHERE username_field = '".$username."'";
	$query_result = $database->query($login_query);

	//conditions
	if($query_result != FALSE) {
		foreach($query_result as $row_query) {
			// check if password are equal
	        if($row_query['password_field']==$password)
	        {
	        	/*
				// remember username & password to session if "Remember me" was set
				*/
	            $_SESSION["username"] = $username;
				$_SESSION["password"] = $password; 
	            header("Location: ../index.html"); /* Redirect browser */
				exit();
	        }
	        else
			{
				echo "<strong>Invalid login info</strong>";
				header("Location: ../login.html"); /* Redirect browser */
				exit();
			}
		}


	}
	else {
		echo "The username you entered is invalid";
	}
}

?>