<?php
	function update_usersTable(string $username, string $password){
		include "connect_db.php";		// Connect to the remote database

		$database->beginTransaction();

		try{
			$query = 'UPDATE users 
					SET username = :username, password = :password WHERE username = :username';

			$statement = $database->prepare($query);
			$statement->bindValue('username', $username);
			$statement->bindValue('password', $password);
			$statement->bindValue('firstName', $firstName);
			$statement->bindValue('lastName', $lastName);
			$statement->bindValue('userId', $userId);

			if(!$statement->execute()){
				throw new Exception('Error - could not update database');
			}
		}
		$database->commit();
		catch (Exception $e) {
			$database->rollBack();
		}
	}

	function update_password(string $username, string $password) {
		include "connect_db.php";		// Connect to the remote database		

		try{
			$query = 'UPDATE users 
					SET password = :password WHERE username = :username';

			$statement = $database->prepare($query);
			$statement->bindValue('username', $username);
			$statement->bindValue('password', $password);
			
			if(!$statement->execute()){
				throw new Exception('Error - could not update password');
			}
		}
		$database->commit();
		catch (Exception $e) {
			$database->rollBack();
		}
	}

?>