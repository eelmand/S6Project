<?php
	include "update_users.php";

	$username = $_SESSION["username"];
	$password = $_POST["password"];
	
	try  {
		update_password($username, $password);	
	}
	catch(Exception $e) {
		$e->getMessage();
	}

	header("Location: ../dashboard.html"); /* Redirect browser */
?>