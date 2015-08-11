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

You will see some warnings about `znc.conf]... [ No such file ]` and `Unrecoverable config error.`, this is fine for now, as we are going to create the config and put it in a different directory than ZNC is expecting it.

### Initial configuration

SSH into your app's gear, and get the IP address which ZNC will bind to:

`rhc ssh znc`

Then, once in the gear, run:

`echo $OPENSHIFT_DIY_IP`

 which will return a an IP address similar to 127.10.10.1. Remember this value for later.

Now armed with this information, we are ready to configure ZNC for first use. First, we need to construct the config file that ZNC was complaining about not finding earlier:

(Execute these commands in the gear. If you've exited out already, simply run `rhc ssh znc` again.)

`cd $OPENSHIFT_DATA_DIR/.local`

Make a directory for the configs: `mkdir configs`
`
Run the znc wizard for generating a config. This will ask a series of questions, where the default answers are mostly fine. Pay particular attention to the port and ip address lines:  `./bin/znc --makeconf`

For the port, OpenShift listens on 8080 (it can be any port in that range, with a few exceptions, but let's use 8080 when the config wizard asks).

The wizard, at the end, will complain that it is `Unable to open file, Please specify an alternate location (or "stdout" for displaying the config)`. We're going to use stdout, copy the text starting with `// WARNING` and ending with `</User>` using vim, add this to the configs dir we created above as `znc.conf`
