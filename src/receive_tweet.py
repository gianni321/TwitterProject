import tweepy
import sys
import datetime
import json
import urllib


# Twitter Tokens
twitter_auth_keys = {
    "consumer_key": "8r3djrKFhQKLFn7pi53VLOAtd",
    "consumer_secret": "m8xIrhQtX6lfSagxbnOQMrNjpVWUCkhX7ccHo7TYOtdV2fBDW6",
    "access_token": "1231271703709286400-cLDovtBPZwJfoHpCptgWqMzHte6d27",
    "access_token_secret": "mTeSKmvavmBFxPX3Drvi7EqAbEpC6BNqZAgjtwHreBVTE"
}
# Loading in consumer tokens
auth = tweepy.OAuthHandler(
    twitter_auth_keys['consumer_key'],
    twitter_auth_keys['consumer_secret']
)
# Loading in access tokens
auth.set_access_token(
    twitter_auth_keys['access_token'],
    twitter_auth_keys['access_token_secret']
)
api = tweepy.API(auth)

# timeline = tweepy.Cursor(api.mentions_timeline).items()
# print(timeline)

# idk = ""
# for mentions in tweepy.Cursor(api.mentions_timeline).items():
#     # f.write(str(mentions))
#     idk = json.loads(str(mentions))

# print(idk)

# f.close()

twt = api.search(q="#weather", since_id=360000000)

for s in twt:
    sn = s.user.screen_name
    m = "HI", (sn)
    s = api.update_status(m, s.id)
    # ('HI', 'GriffinWeather')
