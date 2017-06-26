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
	include "connect_db.php"; // connect to database

	//check if the username entered is in the database.
	$login_query = "SELECT * FROM users WHERE username_field = '".$username."'";
	$query_result = mysql_query($login_query);

	//conditions
	if(mysql_num_rows($query_result)==0) {
	//if username entered not yet exists
	    echo "The username you entered is invalid.";
	}
	else 
	{
		//if exists, then extract the password.
	    while($row_query = mysql_fetch_array($query_result)) {

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
}

?>