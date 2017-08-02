<?php
	session_start();
	$username = $_SESSION["username"];
	$password = $_POST["password"];

	echo '<script>';
	echo 'console.log(' . 'test123' . ')';
	echo '</script>';
	sleep(5);

	include "update_users.php";

	
	try  {
		update_password($username, $password);	
	}
	catch(Exception $e) {
		$e->getMessage();
	}

	header("Location: ../dashboard.html"); /* Redirect browser */
?>