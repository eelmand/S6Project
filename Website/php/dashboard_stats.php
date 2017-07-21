<?php	
	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=127.0.0.1;dbname=elevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		echo "Error: " . $e->getMessage() . "<br />";
		return;
	}

	$stats = ['FLRS_TRVL_DAY', 'FLRS_TRVL_WEEK','MOST_VSTD_FLR'];

	$data = array();

	foreach($stats as $stat) {
		$rows = $database->query("SELECT name, timestamp, value FROM dashboard_stats WHERE name='" .
			$stat . "' ORDER BY timestamp DESC LIMIT 1");

		if($rows != FALSE) {
			foreach($rows as $row){
				$data[$row['name'] . "_VALUE"] = $row['value'];
				$data[$row['name'] . "_TIMESTAMP"] = $row['timestamp'];
			}
		}
		else {
			//echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
		}
	}

	// Encode data into JSON for easy Javascript passing & parsing
	$json_data = json_encode($data);
	echo $json_data;
?>