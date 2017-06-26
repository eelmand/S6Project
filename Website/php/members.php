<?php

include "admin_info.php"; // include Admin Login Info 

session_start();

// Check if user is logged and has a right to access
if (isset($_SESSION["username"]))
{
	if($_SESSION["username"] == $GLOBALS["admin_usr"])
		echo "<strong>Welcome, Admin!</strong>";
	else
		echo "<p>You have no authority here</p>";
}
else
{
	//echo "<strong>You must be logged in!</strong>";
}

?>

