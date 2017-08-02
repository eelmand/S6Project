<?php
	// Make an admin object
	include "users.php";
	$admin = new Admin;

	// Get user info from Javascript
	$username = $_POST["username"];
	echo $username;

	// Grant or revoke access for user
	if (isset($_POST['grant_access'])) {
		$admin->grantAccess($username);
	} 
	// Revoke access from user
	else if (isset($_POST['revoke_access'])) {
	    $admin->revokeAccess($username);
	}

	// Redirect back to user_management.html
	header("Location: ../user_management.html"); /* Redirect browser */
?>