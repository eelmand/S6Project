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

	// Query database for most recent value of each signal
	$signals = ['SM_STATE', 'SM_FLOOR_REQ', 'SC_ENABLE', 'SC_FLOOR_CMD', 'EC_STATE', 
					'EC_CAR_POS', 'F1_CALL_REQ', 'F2_CALL_REQ', 'F3_CALL_REQ', 
					'CC_FLOOR_REQ', 'CC_DOOR_STATE'];

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
	}

	// Encode data into JSON for easy Javascript passing & parsing
	$json_data = json_encode($data);

?>

<script>
	// Make PHP variables available to javascript
<<<<<<< HEAD
	var SM_STATE_RAW = <?php echo $SM_STATE_RAW; ?>;
	var SM_STATE_PHYS = <?php echo "'" . $SM_STATE_PHYS . "'"; ?>;
	var SM_STATE_TIMESTAMP = <?php echo "'" . $SM_STATE_TIMESTAMP . "'"; ?>;

	var SM_FLOOR_REQ_RAW = <?php echo $SM_FLOOR_REQ_RAW; ?>;
	var SM_FLOOR_REQ_PHYS = <?php echo "'" . $SM_FLOOR_REQ_PHYS . "'"; ?>;
	var SM_FLOOR_REQ_TIMESTAMP = <?php echo "'" . $SM_FLOOR_REQ_TIMESTAMP . "'"; ?>;

	var SC_ENABLE_RAW = <?php echo $SC_ENABLE_RAW; ?>;
	var SC_ENABLE_PHYS = <?php echo "'" . $SC_ENABLE_PHYS . "'"; ?>;
	var SC_ENABLE_TIMESTAMP = <?php echo "'" . $SC_ENABLE_TIMESTAMP . "'"; ?>;

	var SC_FLOOR_CMD_RAW = <?php echo $SC_FLOOR_CMD_RAW; ?>;
	var SC_FLOOR_CMD_PHYS = <?php echo "'" . $SC_FLOOR_CMD_PHYS . "'"; ?>;
	var SC_FLOOR_CMD_TIMESTAMP = <?php echo "'" . $SC_FLOOR_CMD_TIMESTAMP . "'"; ?>;

	var EC_STATE_RAW = <?php echo $EC_STATE_RAW; ?>;
	var EC_STATE_PHYS = <?php echo "'" . $EC_STATE_PHYS . "'"; ?>;
	var EC_STATE_TIMESTAMP = <?php echo "'" . $EC_STATE_TIMESTAMP . "'"; ?>;

	var EC_CAR_POS_RAW = <?php echo $EC_CAR_POS_RAW; ?>;
	var EC_CAR_POS_PHYS = <?php echo "'" . $EC_CAR_POS_PHYS . "'"; ?>;
	var EC_CAR_POS_TIMESTAMP = <?php echo "'" . $EC_CAR_POS_TIMESTAMP . "'"; ?>;

	var F1_CALL_REQ_RAW = <?php echo $F1_CALL_REQ_RAW; ?>;
	var F1_CALL_REQ_PHYS = <?php echo "'" . $F1_CALL_REQ_PHYS . "'"; ?>;
	var F1_CALL_REQ_TIMESTAMP = <?php echo "'" . $F1_CALL_REQ_TIMESTAMP . "'"; ?>;
	
	var F2_CALL_REQ_RAW = <?php echo $F2_CALL_REQ_RAW; ?>;
	var F2_CALL_REQ_PHYS = <?php echo "'" . $F2_CALL_REQ_PHYS . "'"; ?>;
	var F2_CALL_REQ_TIMESTAMP = <?php echo "'" . $F2_CALL_REQ_TIMESTAMP . "'"; ?>;

	var F3_CALL_REQ_RAW = <?php echo $F3_CALL_REQ_RAW; ?>;
	var F3_CALL_REQ_PHYS = <?php echo "'" . $F3_CALL_REQ_PHYS . "'"; ?>;
	var F3_CALL_REQ_TIMESTAMP = <?php echo "'" . $F3_CALL_REQ_TIMESTAMP . "'"; ?>;

	var CC_FLOOR_REQ_RAW = <?php echo $CC_FLOOR_REQ_RAW; ?>;
	var CC_FLOOR_REQ_PHYS = <?php echo "'" . $CC_FLOOR_REQ_PHYS . "'"; ?>;
	var CC_FLOOR_REQ_TIMESTAMP = <?php echo "'" . $CC_FLOOR_REQ_TIMESTAMP . "'"; ?>;	

	var CC_DOOR_STATE_RAW = <?php echo $CC_DOOR_STATE_RAW; ?>;
	var CC_DOOR_STATE_PHYS = <?php echo "'" . $CC_DOOR_STATE_PHYS . "'"; ?>;
	var CC_DOOR_STATE_TIMESTAMP = <?php echo "'" . $CC_DOOR_STATE_TIMESTAMP . "'"; ?>;
=======
	var json_data = <?php echo $json_data; ?>;
>>>>>>> php_json
</script>