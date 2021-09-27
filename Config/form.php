<?php
//add form to cookie
if (isset($_GET['name']) && isset($_GET['email']) && isset($_GET['phone'])) {
    $name = $_GET['name'];
    $email = $_GET['email'];
    $phone = $_GET['phone'];
    setcookie("name", $name, time() + (86400 * 30), "/");
    setcookie("email", $email, time() + (86400 * 30), "/");
    setcookie("phone", $phone, time() + (86400 * 30), "/");
}
//print cookies
if (isset($_GET['name']) && isset($_GET['email']) && isset($_GET['phone'])) {
    echo "Name: " . $_GET['name'] . "<br>";
    echo "Email: " . $_GET['email'] . "<br>";
    echo "Phone: " . $_GET['phone'] . "<br>";
}

?>
<!DOCTYPE html>
<html>

<head>
    <title>Form</title>
</head>

<body>
    <form action="form.php" method="post">
        <input type="text" name="name" placeholder="Name">
        <input type="text" name="email" placeholder="Email">
        <input type="text" name="phone" placeholder="Phone">
        <input type="submit" value="Submit">
    </form>

</body>

</html>