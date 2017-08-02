<?php
	session_start();
	$username = $_SESSION["username"];
	$password = $_POST["password"];

	$myquery = "UPDATE users SET password='" . $password . "' WHERE username='" . $username . "'";
	$query_result = $database->query($myquery);

	/*
	include "update_users.php";

	
	try  {
		update_password($username, $password);	
	}
	catch(Exception $e) {
		$e->getMessage();
	}*/

	header("Location: ../dashboard.html"); /* Redirect browser */
?>