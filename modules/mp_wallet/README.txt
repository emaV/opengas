$Id: README.txt,v 1.1 2011/01/25 16:12:04 aronnovak Exp $

MP WALLET
=========

In-site micropayment solution for übercart+übercart marketplace.

Developed by Aron Novak @ Agence Inovae, sponsored by MokaStudio

http://agenceinovae.com
http://drupal.org/user/61864


Features
========

- Each user has its own wallet that stores his balance and transaction history
- The wallet is useable for übercart payment method
-- The wallet is useable for making one-click payment for non-shippable products
- The wallet can be deposited via a 3rd party payment processor (PayPal Express Checkout is supported)
- The balance can be withdrawed from the wallet via a 3rd party payment processor (PayPal MassPay API is supported).
- The users can make donations to each other (like making wire transfers, send free amount)
- The balance is counted in virtual currency, the module handles the exchanges.
- Detailed report interface to have a bird-eye view of the circulation of the wallets.

Requirements
============

- MySQL 5.1.x with InnoDB
- Drupal 6.17 or higher.
- PHP 5.2.x

Installation
============

- Install Übercart Marketplace + MP Wallet.

- Get PayPal API credentials and configure it via admin/store/settings/payment/edit/gateways / PayPal Website Payments Pro settings / API credentials
  At the same page, setup the site currency (Currency code). This is used as a site basic currency, you have to have money in that currency on your
  PayPal account to be able to make withdrawals to the users from the wallet.
  For test API access, visit https://developer.paypal.com/

- Create a site-wallet Drupal user admin/user/user/create and note its userid.

- Configure MP Wallet at admin/store/settings/wallet. You need the userid from the previous step now.
  !! Credit exchange rate, Site-wallet user and Numerical precision settings should not be changed after the site is launched. !!!
  About numerical precision: the module rounds all the values before & after transactions to that precision, for example, if numerical precision is 2
  and the donation amount to the recipient is 5.659 (after fees), the recipient will recieve 5.66.
  However at withdrawal, when sending the amount to PayPal, the module truncats the remaining decimal places to 2 decimal places. It does not cause
  any inconvience if the precision is 2 or lower. Example: withdraw: 2.229 USD, receive: 2.22 USD (with precision 3)

- Enable wallet payment method at admin/store/settings/payment/edit/methods , to be able to make 1-click shopping, you need to make "Marketplace Wallet" method
  the default one

- The users can start to use their wallets. 

User interface walkthrough
==========================

User viewpoint
--------------

1) mp-wallet ; you see a general overview of your wallet.
2) mp-wallet/identifiers ; setup your payment processor identifiers (used for withdrawals)
3) mp-wallet/deposit ; deposit money from PayPal - it's not required to use the same account as supplied in 2)
4) mp-wallet/donate ; donate a free amount to another user. Username selection is helped by autocomplete.
5) mp-wallet/withdraw ; withdraw money from the wallet
6) Go to an übercart product page, you can either click on "Buy this item now!" link for 1-click shopping or compose your übercart shopping cart as
   you'd do normally.
   1-click shopping is redirected back to the product page after completion, the übercart status messages are displayed.
7) Overview your transactions at mp-wallet/history , click on the Details link what appears at each item to see transaction type (sell, withdraw,
   deposit, donation) and details.

Site admin viewpoint
--------------------
1) admin/store/settings/wallet - to control all the settings
2) admin/store/reports/wallet - to see the transaction amounts filtered by transaction type (Deposits, Sales, Donations, Withdrawals - the tabs) and can be
   grouped by various granularities.
3) admin/store/reports/wallet/stats - statistics about the site, total amount in circulation, average balance, transaction type percentage
4) Login as site-wallet Drupal user and go to mp-wallet ; you see the total amount of commissions that the site gained.
   Normal wallet functions are not available with this account, you can't use it for deposit, withdraw, donation and shopping.
   This account can't act as a seller neither a buyer as well.

