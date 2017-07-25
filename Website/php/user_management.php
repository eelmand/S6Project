<?php
	// Get user info from Javascript
	$username = $_POST["username"];
	echo $username;

	include "connect_db.php";		// Connect to the remote database

	// Grant or revoke access for user
	if (isset($_POST['grant_access'])) {
		// Query for first name, last name and password based on 
		$rows = $database->query("SELECT username, password, first_name, last_name, email, last_login FROM new_users WHERE username='" .
				$username . "' LIMIT 1");

		if($rows != FALSE) {
			foreach($rows as $row){
				$username = $row['username'];
				$password = $row['password'];
				$first_name = $row['first_name'];
				$last_name = $row['last_name'];
				$email = $row['email'];
				$last_login = $row['last_login'];

				// Prep a query for inputting into the database
				$query = 'INSERT INTO users(username, password, first_name, last_name, email, last_login) VALUES(:username, :password, :first_name, :last_name, :email, :last_login)';
				$statement = $database->prepare($query);
				
				$params = [
					'username' => $username,
					'password' => $password,
					'first_name' => $first_name,
					'last_name' => $last_name,
					'email' => $email,
					'last_login' => $last_login
				];

				// Execute the query
				$result = $statement->execute($params);

				// Delete user from new_users table
				$database->query("DELETE FROM new_users WHERE username='" . $username . "'");

				// Send email to user letting them know they have been granted access
				$to = $email;
				$subject = 'Access to AdequateElevators.com granted';
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
						<form class="center-block" action="http://adequateelevators.com/Website/login.html" id="login" method="post">
							<h3>An administrator has granted you access to adequateelevators.com</h3>
							<p id="username">Username: ' . $username . ' </p>
							<button type="submit" class="btn btn-default">Login</button>
						</form>
					</body>
					</html>		
				';


				mail($to, $subject, $msg, $headers);


			}
		}
		else {
			header("Location: ../user_management.html"); /* Redirect browser */
			exit();
		}
	} 
	// Revoke access from user
	else if (isset($_POST['revoke_access'])) {
	    // Simple delete query
	    $database->query("DELETE FROM users WHERE username='" . $username . "'");
	}

	// Redirect back to user_management.html
	header("Location: ../user_management.html"); /* Redirect browser */
?>