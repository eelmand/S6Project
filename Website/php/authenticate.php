<?php

include "admin_info.php"; // include Admin Login Info 

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
	if(($username == $GLOBALS["admin_usr"]) && ($password == $GLOBALS["admin_pwd"]))
	{
		$_SESSION["username"] = $username;
		$_SESSION["password"] = $password; 
		
/*
		// remember username & password to session if "Remember me" was set
		if($remember){

		}
*/
		echo "<strong>Welcome, ESE-guru!</strong>";
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

?>