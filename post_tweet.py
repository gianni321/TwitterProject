import tweepy
import sys
import datetime


'''
GRV post_tweet.py.
How TO Run: $python post_tweet.py file.txt
Pass in a file that has the contents of what should be tweeted out.
The current date will be appended to the begining of the tweet. 
@WARNING This code will not be able to post the same status twice. @Fix by adding in date.
'''


def post_tweet(tweet):
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
    # Verify auth
    api = tweepy.API(auth)
    # Seting "@var tweet" to be posted as status.
    status = api.update_status(status=tweet)


if __name__ == "__main__":
    # Error checking
    if (len(sys.argv) != 2):
        print("Must pass in file to tweet. Exiting.")
        exit()

    # Open File
    with open(sys.argv[1], 'r') as f:
        contents = f.read()
    # Get date
    now = datetime.datetime.now()
    # Format date
    now = now.strftime("%Y-%m-%d %H:%M")
    # Show what will be printed (May need to be removed)
    print("This is the content that will be tweeted out: " +
          str(now) + "\n" + contents)
    # Load into our post tweet with date
    tweet = str(now) + "\n" + contents
    post_tweet(tweet)
