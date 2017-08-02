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


    // Now process data and request access
    include "users.php";
    $user = new User($_POST["username"], $_POST["password"], $_POST["first_name"], $_POST["last_name"], $_POST["email"]);
    try {
        $user->requestAccess();    
    }
    catch(Exception $e) {
        echo $e->getMessage();
    }
?>
