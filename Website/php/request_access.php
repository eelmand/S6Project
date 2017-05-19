<?php
$submitted = !empty($_POST);
?>
<!DOCTYPE html>
<html>
	<head>
		<title>Form Handler</title>
	</head>
	<body>
		<p>Form Submitted? <?php echo (int) $submitted; ?></p>
	</body>
</html>