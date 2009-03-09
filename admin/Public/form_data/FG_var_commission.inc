<?php

getpost_ifset(array('id', 'card_id', 'date', 'payment','description','added_refill','refill_type'));


if (!isset($form_action) || $form_action=="list") {
	$HD_Form = new FormHandler("cc_agent_commission LEFT JOIN cc_card ON cc_card.id=cc_agent_commission.id_card","Commission's Agents");
} else {
	$HD_Form = new FormHandler("cc_agent_commission","Commission");
}

$HD_Form -> FG_TABLE_ID = 'cc_agent_commission.id';

$HD_Form -> FG_DEBUG = 0;
$HD_Form -> FG_TABLE_DEFAULT_SENS = "DESC";

$HD_Form ->FG_LIST_ADDING_BUTTON1 = true;
$HD_Form ->FG_LIST_ADDING_BUTTON_LINK1 = "A2B_entity_commission_agent.php?form_action=ask-add&section=2";
$HD_Form ->FG_LIST_ADDING_BUTTON_ALT1 = $HD_Form ->FG_LIST_ADDING_BUTTON_MSG1 = gettext("Add Commission");
$HD_Form ->FG_LIST_ADDING_BUTTON_IMG1 = Images_Path ."/money_add.png" ;
$paid_status_list = Constants::getInvoicePaidStatusList();
$HD_Form -> AddViewElement(gettext("ID"), "cc_agent_commission.id", "10%", "center", "sort");
$HD_Form -> AddViewElement(gettext("ACCOUNT"), "username", "20%", "center", "sort", "", "30", "", "", "", "", "linktocustomer");
$HD_Form -> AddViewElement(gettext("PAYMENT DATE"), "date", "20%", "center", "sort", "30", "", "", "", "", "", "display_dateformat");
$HD_Form -> AddViewElement(gettext("AMOUNT"), "amount", "10%", "center", "sort");
$HD_Form -> AddViewElement(gettext("PAID STATUS"),"payment_type", "7%", "center", "sort", "", "list", $paid_status_list);
$HD_Form -> AddViewElement(gettext("LINK TO PAYMENT"), "id_payment", "20%", "center", "sort", "", "lie_link", "cc_payment", "payment, id", "id='%id'", "%1 ".BASE_CURRENCY." (id:%2)", "", "A2B_entity_payment.php");

$HD_Form -> FieldViewElement ('cc_agent_commission.id, username, date, amount ,paid_status,id_payment');


$HD_Form -> CV_NO_FIELDS  = gettext("THERE IS NO ".strtoupper($HD_Form->FG_INSTANCE_NAME)." CREATED!"); 
$HD_Form -> CV_DISPLAY_LINE_TITLE_ABOVE_TABLE = false;
$HD_Form -> CV_TEXT_TITLE_ABOVE_TABLE = '';
$HD_Form -> CV_DISPLAY_FILTER_ABOVE_TABLE = false;


$HD_Form -> FG_EDITION = true;
$HD_Form -> FG_DELETION = true;

if ($form_action=="ask-add" && !empty($card_id)) {
	$id_val = "value='$card_id'";
}

$HD_Form -> AddEditElement (gettext("CUSTOMER ID"),
			   "id_card",		
			   "$value",	
			   "POPUPVALUE",	
			   "size=30 maxlength=50 ".$id_val,	
			   "4",	
			   gettext("Insert the Customer ID "),
			    "" , "", "", "", "", 				
				"A2B_entity_card.php?popup_select=1&"
				, ", 'CardNumberSelection','width=550,height=330,top=20,left=100,scrollbars=1'" ,
				gettext("Select the Customer ID"));
			   
if ($form_action=="ask-add") {	
	$begin_date = date("Y");
	$end_date = date("-m-d H:i:s");
	$comp_date=$begin_date.$end_date;
	$comp_date="value='$comp_date'";
}

$HD_Form -> AddEditElement (gettext("PAYMENT DATE"),
			   "date",		
			   '$value',	
			   "INPUT",	
			   "size=40 READONLY maxlength=40  $comp_date",	
			   "10",	
			   gettext("Insert the current date"),
			   "" , "", "",	"", "", "", "", "" );

$HD_Form -> AddEditElement (gettext("COMMISSION AMOUNT"),
			   "payment",		
			   '$value',	
			   "INPUT",	
			   "size=60 maxlength=10",	
			   "12",	
			   gettext("Insert the commission amount"),
			   "" , "", "",	"", "" , "", "", gettext("Enter the amount in the currency base : ").BASE_CURRENCY );


$HD_Form -> AddEditElement (gettext("DESCRIPTION"),
				"description",
				'',
				"TEXTAREA",
				"cols=50 rows=4",
				"",
				gettext("Insert the description"),
				"" , "", "", "", "" , "", "", "");

$HD_Form -> AddEditElement (gettext("PAYMENT ID"),
			   "id_payment",		
			   "$value",	
			   "POPUPVALUE",	
			   "size=30 maxlength=50 ".$id_val,	
			   "4",	
			   gettext("Insert the Payment ID "),
			    "" , "", "", "", "", 				
				"A2B_entity_payment.php?popup_select=1&"
				, ", 'PaymentSelection','width=550,height=330,top=20,left=100,scrollbars=1'" ,
				gettext("Select the Payment ID"));

$HD_Form -> AddEditElement (gettext("PAID STATUS"),
               "paid_status",
               '$value',
               "SELECT",
               "",
               "",
               "",
               "list" , "", "",     "", $paid_status_list, "%1", "", gettext("Define if this commission is paid or not.") );

$HD_Form -> FieldEditElement ('id_card, date, payment, description,id_payment, payment_type');



$HD_Form -> FG_FILTER_APPLY = true;
$HD_Form -> FG_FILTERFIELD = 'cardnumber';
$HD_Form -> FG_FILTERFIELDNAME = 'account number';
$HD_Form -> FG_FILTER_FORM_ACTION = 'list';

if (isset($filterprefix)  &&  (strlen($filterprefix)>0)) {
	if (strlen($HD_Form -> FG_TABLE_CLAUSE)>0) $HD_Form -> FG_TABLE_CLAUSE.=" AND ";
	$HD_Form -> FG_TABLE_CLAUSE.="username like '$filterprefix%'";
}



$HD_Form -> FG_INTRO_TEXT_EDITION= gettext("You can modify, through the following form, the different properties of your ".$HD_Form->FG_INSTANCE_NAME);
$HD_Form -> FG_INTRO_TEXT_ASK_DELETION = gettext("If you really want remove this ".$HD_Form->FG_INSTANCE_NAME.", click on the delete button.");
$HD_Form -> FG_INTRO_TEXT_ADD = gettext("you can add easily a new ".$HD_Form->FG_INSTANCE_NAME.".<br>Fill the following fields and confirm by clicking on the button add.");


$HD_Form -> FG_INTRO_TEXT_ADITION = '';
$HD_Form -> FG_TEXT_ADITION_CONFIRMATION = gettext("Your new ".$HD_Form->FG_INSTANCE_NAME." has been inserted. <br>");


$HD_Form -> FG_BUTTON_EDITION_SRC = $HD_Form -> FG_BUTTON_ADITION_SRC  = Images_Path . "/cormfirmboton.gif";
$HD_Form -> FG_BUTTON_EDITION_BOTTOM_TEXT = $HD_Form -> FG_BUTTON_ADITION_BOTTOM_TEXT = gettext("Click 'Confirm Data' to continue.");


$HD_Form -> FG_GO_LINK_AFTER_ACTION_ADD = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_EDIT = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";
$HD_Form -> FG_GO_LINK_AFTER_ACTION_DELETE = $_SERVER['PHP_SELF']."?atmenu=document&stitle=Document&wh=AC&id=";



