<?php
	
	$SM_STATE_RAW = -1;
	$SM_STATE_PHYS = -1;
	$SM_STATE_TIMESTAMP = -1;

	$SM_FLOOR_REQ_RAW = -1;
	$SM_FLOOR_REQ_PHYS = -1;
	$SM_FLOOR_REQ_TIMESTAMP = -1;	

	$SC_ENABLE_RAW = -1;
	$SC_ENABLE_PHYS = -1;
	$SC_ENABLE_TIMESTAMP = -1;

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

	foreach($signals as $signal) {
		$rows = $database->query("SELECT name, timestamp, raw, phys FROM signals WHERE name='" .
			$signal . "' ORDER BY timestamp DESC LIMIT 1");


		if($rows != FALSE) {
			foreach($rows as $row){
				${$row['name'] . '_RAW'} = $row['raw'];
				${$row['name'] . '_PHYS'} = $row['phys'];
				${$row['name'] . '_TIMESTAMP'} = $row['timestamp'];
			}
		}
	}
?>

<script>
	// Make PHP variables available to javascript
	var SM_STATE_RAW = <?php echo $SM_STATE_RAW; ?>;
	var SM_STATE_PHYS = <?php echo "'" . $SM_STATE_PHYS . "'"; ?>;
	var SM_STATE_TIMESTAMP = <?php echo "'" . $SM_STATE_TIMESTAMP . "'"; ?>;

	var SM_FLOOR_REQ_RAW = <?php echo $SM_FLOOR_REQ_RAW; ?>;
	var SM_FLOOR_REQ_PHYS = <?php echo "'" . $SM_FLOOR_REQ_PHYS . "'"; ?>;
	var SM_FLOOR_REQ_TIMESTAMP = <?php echo "'" . $SM_FLOOR_REQ_TIMESTAMP . "'"; ?>;

	var SC_ENABLE_RAW = <?php echo $SC_ENABLE_RAW; ?>;
	var SC_ENABLE_PHYS = <?php echo "'" . $SC_ENABLE_PHYS . "'"; ?>;
	var SC_ENABLE_TIMESTAMP = <?php echo "'" . $SC_ENABLE_TIMESTAMP . "'"; ?>;


</script>