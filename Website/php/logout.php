<?php
	include "users.php";

	// Create a blank user to use the logout function
	$user = new User;
	try {
		$user->logout();	
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}
	
?>