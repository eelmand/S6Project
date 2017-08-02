<?php
	function update_usersTable(int $userId, string $username, string $password, string $firstName, string $lastName){
		include "connect_db.php";		// Connect to the remote database

		$database->beginTransaction();

		try{
			$query = 'UPDATE users 
					SET username = :username, password = :password, firstName = :firstName, lastName = :lastName
					WHERE userId = :userId';

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
?>