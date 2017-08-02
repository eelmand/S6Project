<?php
	// Class definition for normal users	
	class User {
		// Properties of a User
		private $username;
		private $password;
		private $id;
		private $level = 0;	// Users are always level 0
		private $firstName;
		private $lastName;
		private $email;
		private $lastLogin;

		// Constructor for logging out a user (i.e. don't care about username or password)
		public function __construct() {}

		// Constructor for when users login (i.e. only username and password provided)
		public function __construct(string $user, string $pwd) {
			$this->username = $user;
			$this->password = $pwd;
		}


		// Constructor for when new users request access (i.e. all info provided)
		public function __construct(string $user, string $pwd, string $first, string $last, string $mail) {
			$this->username = $user;
			$this->password = $pwd;
			$this->firstName = $first;
			$this->lastName = $last;
			$this->email = $mail;
		}

		// Accessor functions for the User class
		public function getId() : int {
			return $this->id;
		}

		public function getLevel() : int {
			return $this->level;
		}

		public function getUsername() : string {
			return $this->username;
		}

		public function getPassword() : string {
			return $this->password;
		}

		public function getFirstName() : string {
			return $this->firstName;
		}

		public function getLastName() : string {
			return $this->lastName;
		}
		
		public function getEmail() : string {
			return $this->email;
		}
		
		public function getLastLogin() : string {
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
?>