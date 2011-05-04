$Id

The Tokenize Request Parameters module is intended to provide means to display
parameters that are passed to a page either in the URL (GET method) or from a
form post (POST method). In cases where you might direct your users to a third
party transaction site, such as a payment processor or other transactional service
and want to be able to display transactional data passed back from that third
party site (e.g. a confirmation number, order number, final price etc.) back to
your user then Tokenize Request Parameters will allow you to display that
information anywhere within your pages.

To use this module you should have the Token Filter module installed and
configured to ensure that content editors have permission to add tokens to
content pages. You must then configure the token settings to specify what
request methods (GET and/or POST) can be used to tokenize parameters and which
parameters should be made into tokens. Specify also on which pages request
parameters will be exposed.

Be restrictive as possible when configuring what pages and parameters will be
exposed as tokens and be mindful of possible security threats. Be particularly
cautious when dealing with sensitive data.

To use the tokens in your pages you should use the Token Filter module to
enable the use of tokens within the content form for your content types.
Parameters will be referenced via Token Filter via the token template:
[token global get-param-{yourparam}]. For example: if you have a parameter
passed on the URL called 'ordernum' (&ordernum=3432) then you will use the
token [token global get-param-ordernum]. This token would be replaced by the
value '3432'. If this parameter is passed from a form using the POST method
instead, you would use the token [token global post-param-ordernum]. Easy!

TO INSTALL:

* Download & unpack the archive file

* Put the unarchived folder into the 'sites/all/modules' directory, or into the 
  equivalent subsite modules directory. If you have a subsite called 'mysubsite.com'
  Then place the module directory in the 'sites/mysubsite.com/modules' directory. You
  only need to do this if you want this module be available to that one subsite
  and not to all of your sites. If you want to enable the module on more than one of
  your sites then simply put it in 'sites/all/modules'.

* Log in to Drupal and go to the Admin area. Then navigate to Site Building / Modules.

* Scroll down to the 'Others' block, until you see the Tokenize Request Parameters 
  module listed. Select 'Enable' and save the form.

* That's all. You will need to go to Admin / Site Settings / Tokenize Request Parameters
  to configure the module to recognize the parameters you want to tokenize and where 
  (i.e. on what pages with parameters be sent).

TO UNINSTALL:

* Tokenize Request Parameters has an uninstaller that will clean out configuration 
  settings from Drupal so that Drupal will be set back to the same state as before the
  module was installed. It is safe to install this module to try it out because we clean
  up after ourselves if the module is not what you are looking for.

* To uninstall: First disable the module so it is no longer active.

* Then go to the 'Uninstall' tab at the top of the page.

* If you have disabled the module successfully you will see a checkbox to uninstall
  Token Request Parameters. Check that and click the 'uninstall' button.

* It will ask you to confirm that you want to uninstall the module. Click the button
  to confirm your intention to remove the module.

* The module resources will be removed and you should see a message saying that variables
  were removed.

* Finally, delete the token_request_params directory from your modules directory and you
  will have a nice clean Token Request Parameter free Drupal installation again.