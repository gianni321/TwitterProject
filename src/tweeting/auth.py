import tweepy


def getAuth():
    print("Authorizing...", flush=True)
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
    # Verify auth
    api = tweepy.API(auth)
    return api
