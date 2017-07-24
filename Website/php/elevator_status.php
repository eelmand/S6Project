<?php	
	include "connect_db.php";		// Connect to the remote database

	// Query database for most recent value of each signal (EXCEPT 'SM_FLOOR_REQ')
	$signals = ['SM_STATE', 'SC_ENABLE', 'SC_FLOOR_CMD', 'EC_STATE', 
					'EC_CAR_POS', 'F1_CALL_REQ', 'F2_CALL_REQ', 'F3_CALL_REQ', 
					'CC_FLOOR_REQ', 'CC_DOOR_STATE'];

	date_default_timezone_set('America/Detroit')
	$status = False;
	foreach($signals as $signal) {
		$rows = $database->query("SELECT name, timestamp, raw, phys FROM signals WHERE name='" .
			$signal . "' ORDER BY timestamp DESC LIMIT 1");

		if($rows != FALSE) {
			foreach($rows as $row){
				$signalTimestamp = strtotime($row['timestamp']);
				$nowTimestamp = strtotime("now");
				$nowMinusTwoMins = $nowTimestamp - (60*2);
				
				if($nowMinusTwoMins < $signalTimestamp){
					$status = True;
				}
			}
			
		}
		else {
			//echo "<script type='text/javascript'> console.log('ERROR: Query returned nothing.') </script>";
		}
	}
	if($status){
		echo "True";
	}
	else{
		echo "False";
	}
	
?>