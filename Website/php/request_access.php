<?php
	// Redirect user to access_requested.html page so they don't have to wait
	// https://stackoverflow.com/questions/10504753/how-to-cause-a-redirect-to-occur-before-php-script-finishes
	header("Location: ../access_requested.html");
	
	// Erase output buffer
	ob_end_clean();

    //Tell the browser that the connection's closed
    header("Connection: close");

    //Ignore the user's abort (which we caused with the redirect).
    ignore_user_abort(true);
    //Extend time limit to 30 minutes
    set_time_limit(1800);
    //Extend memory limit to 10MB
    ini_set("memory_limit","10M");
    //Start output buffering again
    ob_start();

    //Tell the browser we're serious... there's really
    //nothing else to receive from this page.
    header("Content-Length: 0");

    //Send the output buffer and turn output buffering off.
    ob_end_flush();
    flush();
    //Close the session.
    session_write_close();


    // Now process data and send email

	// Get user info from Javascript
	$username = $_POST["username"];
	$password  = $_POST["password"];
	$first_name = $_POST["first_name"];
	$last_name = $_POST["last_name"];

	// Try to connect to database and catch errors
	try {
		$database = new PDO('mysql:host=127.0.0.1;dbname=elevator', 'root', 'password');	
	}
	catch (PDOException $e) {
		//echo "Error: " . $e->getMessage() . "<br />";
		return;
	}

	// Prep a query for inputting into the database
	$query = 'INSERT INTO new_users (username, password, first_name, last_name) VALUES(:username, :password, :first_name, :last_name)';
	$statement = $database->prepare($query);
	
	$params = [
		'username' => $username,
		'password' => $password,
		'first_name' => $first_name,
		'last_name' => $last_name
	];

	// Execute the query
	$result = $statement->execute($params);

	// Send email to admins asking if they want to approve or deny the person
	$subject = 'Access request for AdequateElevators.com';
	$headers = "From: webmaster@adequateelevators.com" . PHP_EOL;
	$headers .= "Reply-To: webmaster@adequateelevators.com" . PHP_EOL;
	$headers .= "X-Mailer: PHP/" . phpversion();
    $headers .= "MIME-Version: 1.0" . PHP_EOL;
    $headers .= "Content-Type: text/html; charset=ISO-8859-1" . PHP_EOL;

	$msg = '
		<?php
			$username = $_POST["username"];
			echo $username;
		?>

		<!DOCTYPE html>
		<html>
		<body>
			<form class="center-block" action="http://adequateelevators.com/php/test.php" id="login" method="post">
				<h1>A new user has requested access to adequateelevators.com</h1>
				<p id="username">Username: test</p>
				<input id="usr" name="username" value="test" type="hidden"/>
				<button type="submit" class="btn btn-default">Grant Access</button>
			</form>
		</body>
		</html>		
	';


	mail("thomas.abdallah@gmail.com", $subject, $msg, $headers);
?>
