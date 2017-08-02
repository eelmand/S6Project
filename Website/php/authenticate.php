<?php
	include "users.php";
	$user = new User($_POST["username"], $_POST["password"]);
	
	try {
		$user->login();
	}
	catch(Exception $e) {
		echo $e->getMessage();
	}
?>