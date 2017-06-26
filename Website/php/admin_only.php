<?php
session_start();

//include "admin_info.php"; // include Admin Login Info 

// Check if user is not logged in or not admin
if (isset($_SESSION["username"])==0)
{
	echo "<p>Access denied</p>";
	sleep(1);
	header("Location: index.html"); /* Redirect browser */
	exit();
}
else
{
	// Access permitted
}
?>

