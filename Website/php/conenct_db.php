<?php
	echo "<script type='text/javascript'> console.log('CONNECTING TO DATABASE') </script>";
	
	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=127.0.0.1;dbname=elevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		echo "Error: " . $e->getMessage() . "<br />";
	}

	echo "<script type='text/javascript'> console.log('CONNECTED TO DATABASE') </script>";

?>