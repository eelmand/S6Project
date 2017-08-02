<?php
	include "users.php";
	$user = new User($_POST["username"], $_POST["password"]);
	$user.login();
?>