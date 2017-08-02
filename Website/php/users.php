<?php
	// Class definition for normal users	
	class User {
		// Properties of a User
		protected $username;
		protected $password;
		protected $id;
		private $level = 0;	// Users are always level 0
		protected $firstName;
		protected $lastName;
		protected $email;
		protected $lastLogin;

		public function __construct() {
			$argv = func_get_args();
			switch( func_num_args()) {
				case 2:
					$this->username = $argv[0];
					$this->password = $argv[1];

				case 5:
					$this->username = $argv[0];
					$this->password = $argv[1];
					$this->firstName = $argv[2];
					$this->lastName = $argv[3];
					$this->email = $argv[4];
			}
		}		

		// Accessor functions for the User class
		public function getId(){
			return $this->id;
		}

		public function getLevel(){
			return $this->level;
		}

		public function getUsername(){
			return $this->username;
		}

		public function getPassword(){
			return $this->password;
		}

		public function getFirstName(){
			return $this->firstName;
		}

		public function getLastName(){
			return $this->lastName;
		}
		
		public function getEmail(){
			return $this->email;
		}
		
		public function getLastLogin(){
			return $this->lastLogin;
		}

		// Login, logout, request access functions
		public function requestAccess() {
			include "connect_db.php";		// Connect to the remote database			

			// Prep a query for inputting into the database
			$query = 'INSERT INTO new_users (username, password, first_name, last_name, email) VALUES(:username, :password, :first_name, :last_name, :email)';
			$statement = $database->prepare($query);
			
			$params = [
				'username' => $this->username,
				'password' => $this->password,
				'first_name' => $this->firstName,
				'last_name' => $this->lastName,
				'email' => $this->email
			];

			// Execute the query
			$result = $statement->execute($params);

			// Send email to admins asking if they want to approve or deny the person
			$to = 'tabdallah1518@conestogac.on.ca, deelman-cc@conestogac.on.ca, srashevskyi8178@conestogac.on.ca';
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
					<h3>A new user has requested access to adequateelevators.com</h3>
					<a href="http://adequateelevators.com/Website/user_management.html">Grant Access to User :</a> ' . $username .'
				</body>
				</html>		
			';

			mail($to, $subject, $msg, $headers);			
		}	// End of requestaccess function

		public function login() {
			session_start();
			include "connect_db.php";		// Connect to the remote database

			//check if the username entered is in the database.
			$login_query = "SELECT * FROM users WHERE username = '".$this->username."'";
			$query_result = $database->query($login_query);

			//conditions
			if($query_result != FALSE) {
				foreach($query_result as $row_query) {
					// check if password are equal
			        if($row_query['password']==$this->password)
			        {
						// remember username & password to session if "Remember me" was set
			            $_SESSION["username"] = $this->username;
						$_SESSION["password"] = $this->password; 

						// Update last login time for this user
						$timestamp_query = "UPDATE users SET last_login=NOW() WHERE username='" . $this->username ."'";
						$query_result = $database->query($timestamp_query);
						// Not checking result for now

			            header("Location: ../dashboard.html"); // Redirect browser
			            exit();
			        }
			        else
					{
						echo "Invalid login info.";
						header("Location: ../login.html"); // Redirect browser
						exit();
					}
				}


			}
			
			echo "Invalid login info.";
			header("Location: ../login.html"); // Redirect browser
			exit();			
		}	// End of login function

		public function logout() {
			session_start();
			session_destroy();

			echo "<p>You have been successfully logged out!</p>";
			sleep(1);
			header("Location: ../login.html"); // Redirect browser
			exit();
		}	// End of logout function	

	}	// End of user class

	class Admin extends User {
		private $level = 1;	// Admin are always level 1
		public function __construct() {
		}

		public function grantAccess($username) {
			include "connect_db.php";		// Connect to the remote database

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
					if ($email != NULL) {
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
								<h3>An administrator has granted you access to adequateelevators.com</h3>
								<a href="http://adequateelevators.com/Website/login.html">Login Page</a>
							</body>
							</html>		
						';


						mail($to, $subject, $msg, $headers);
					}
				}
			}
			else {
				header("Location: ../user_management.html"); /* Redirect browser */
				exit();
			}
		}	// End of grantAccess function

		public function revokeAccess($username) {
			include "connect_db.php";		// Connect to the remote database
	    	$database->query("DELETE FROM users WHERE username='" . $username . "'");

		}
	}	// End of admin class
?>