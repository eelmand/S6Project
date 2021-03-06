<?php

	include "connect_db.php";		// Connect to the remote database

	// Query database for most recent value of each signal
	$signals = ['SM_STATE', 'SM_FLOOR_REQ', 'SC_ENABLE', 'SC_FLOOR_CMD', 'EC_STATE', 
					'EC_CAR_POS', 'F1_CALL_REQ', 'F2_CALL_REQ', 'F3_CALL_REQ', 
					'CC_FLOOR_REQ', 'CC_DOOR_STATE', 'REMOTE_REQ'];

	$data = array();

	foreach($signals as $signal) {
		$rows = $database->query("SELECT name, timestamp, raw, phys FROM signals WHERE name='" .
			$signal . "' ORDER BY timestamp DESC LIMIT 1");

		if($rows != FALSE) {
			foreach($rows as $row){
				$data[$row['name'] . "_RAW"] = $row['raw'];
				$data[$row['name'] . "_PHYS"] = $row['phys'];
				$data[$row['name'] . "_TIMESTAMP"] = $row['timestamp'];
			}
		}
		else {
			//echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
		}
	}

	// Encode data into JSON for easy Javascript passing & parsing
	$json_data = json_encode($data);

	if(file_put_contents('test.json', $json_data) == FALSE) {
		echo "<p>Failed to write data to JSON file.</p>";
	}


	echo $json_data;
?>