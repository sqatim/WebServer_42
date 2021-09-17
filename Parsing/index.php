<html>
<head><?php header("test: abcdef"); ?><meta charset="utf-8"/></head>
<body>

    

    <?php

    echo '<script src="https://code.jquery.com/jquery-3.6.0.min.js" integrity="sha256-/xUj+3OJU5yExlq6GSYGSHk7tPXikynS7ogEvDej/m4=" crossorigin="anonymous"></script>'; 
    print_r($_SERVER);

    echo '<br/>';
    echo '<br/>';

    echo "POST : ";
    print_r($_POST);
    echo '<br/>';
    echo '<br/>';

    echo "GET : ";
    print_r($_GET);


    ?>

</body>


</html>