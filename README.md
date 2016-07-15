# ZNC for OpenShift

[ZNC](http://wiki.znc.in/ZNC) is an IRC bouncer, which will allow you to connect to IRC servers. This quickstart will help you to deploy it seamlessly on the OpenShift platform.

## Running ZNC on OpenShift

### Initial deployment
First, create a diy application:

`rhc create-app znc diy-0.1`

`cd znc`

`git remote add upstream -m master https://github.com/cjryan/znc-openshift-quickstart.git`

`git pull -s recursive -X theirs upstream master`

`git push --force`

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

Run the znc wizard for generating a config. This will ask a series of questions, where the default answers are mostly fine. Pay particular attention to the port and ip address lines:  `./bin/znc --makeconf`

For the port, OpenShift listens on 8181 (it can be any port in that range, with a few exceptions, but let's use 8181 when the config wizard asks).

The wizard, at the end, will complain that it is `Unable to open file, Please specify an alternate location (or "stdout" for displaying the config)`. We're going to use stdout, copy the text starting with `// WARNING` and ending with `</User>` using vim, add this to the configs dir we created above as `znc.conf`

Before you save the file, add `Host = 127.10.10.1`, replacing `127.10.10.1` with whatever your `OPENSHIFT_DIY_IP` is from above. Then, save the file.

Once you've done this, you're ready to run ZNC for the first time.

### Running ZNC

In the `$OPENSHIFT_DATA_DIR/.local` directory, run `./bin/znc --datadir .`

This will then start up znc, which if successful should report:

`[ >> ] ok

[ .. ] Forking into the background...

[ >> ] [pid: 80928]

[ ** ] ZNC 1.4 - http://znc.in`

Once this occurs, you can use your favorite IRC chat client to connect. The ZNC docs are particularly helpful in this regard. Also, you may need to port-forward your app to your local machine using 'rhc port-forward -a <your app name>'.

Until the next version of OpenShift is available (shortly), you can also connect to the webconsole of znc over the portforwarded ip address, e.g. localhost:8181.

### Connecting with a client

ZNC provides several guides for popular IRC chat clients. For an excellent command line client, see [weechat](http://wiki.znc.in/Weechat), or [Pidgin](http://wiki.znc.in/Pidgin)

#### Konversation
To connect with KDE's Konversation IRC client it is recommended to setup a new identity. In that identity change `Auto Identify` from `Standard NickServ` to `Server Password`. The password format for a non-ssl secured connection is `<username>:<password>`.
