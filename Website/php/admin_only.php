<?php

include "admin_info.php"; // include Admin Login Info 

session_start();

// Check if user is not logged in or not admin
if ((isset($_SESSION["username"])==0) || ($_SESSION["username"] != $GLOBALS["admin_usr"]))
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

