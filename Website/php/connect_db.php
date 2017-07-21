<?php
	echo "<script type='text/javascript'> console.log('CONNECTING TO DATABASE') </script>";
	
	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=23.229.227.71;dbname=adequateelevators', 'adequateadmin', 'adequatepassword');	
	}
	catch (PDOException $e) {
		echo "Error: " . $e->getMessage() . "<br />";
	}

	echo "<script type='text/javascript'> console.log('CONNECTED TO DATABASE') </script>";

?>