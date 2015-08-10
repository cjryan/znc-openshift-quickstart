# ZNC for OpenShift

ZNC is an IRC bouncer, which will allow you to connect to IRC servers. This quickstart will help you to deploy it seamlessly on the OpenShift platform.

## Running ZNC on OpenShift

### Initial deployment
First, create a diy application:

`rhc create-app znc diy-0.1`
`cd znc`
`git remote add upstream -m master https://github.com/cjryan/znc-openshift-quickstart.git`
`git pull -s recursive -X theirs upstream master`
`git push`

The initial git push (deployment) takes some time, as the code is compiled on the gear. Once this is done, you'll need to collect some information to setup ZNC for the first time.

### Initial configuration

SSH into your app's gear, and get the IP address which ZNC will bind to:

`rhc ssh znc`

Then, once in the gear, run:

`echo $OPENSHIFT\_DIY\_IP`

 which will return a an IP address similar to 127.10.10.1. Save this value for later.
