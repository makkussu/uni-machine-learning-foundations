import gymnasium as gym
import numpy as np
import matplotlib.pyplot as grapgh

# Creating the environment
env = gym.make("Taxi-v3")

# Initializing Q-table
state_size = env.observation_space.n
action_size = env.action_space.n
q_table = np.zeros((state_size, action_size))

# Hyperparameters
total_episodes = 2000
steps = 200
alpha = 0.7
gamma = 0.6
epsilon = 1.0
min_epsilon = 0.01
decay_rate = 0.005

# Function to choose an action using epsilon-greedy policy
def choose_action(state):
    if np.random.rand() < epsilon:
        return env.action_space.sample()
    else:
        return np.argmax(q_table[state, :])

# Training Q-table
scores = []
for ep_num in range(total_episodes):
    observation, info = env.reset()
    ep_score = 0

    for step in range(steps):
        # random action - replace this with picking the action from the q-table using the epsilon greedy policy
        action = choose_action(observation)
        next_observation, reward, terminated, truncated, info = env.step(action)

        ep_score += reward
        # Update Q-table
        q_table[observation, action] += alpha * (reward + gamma * np.max(q_table[next_observation, :]) - q_table[observation, action])

        observation = next_observation
        if terminated:
            break

    # Decay exploration rate
    epsilon = min_epsilon + (1 - min_epsilon) * np.exp(-decay_rate * ep_num)

    scores.append(ep_score)
    print(f"Episode {ep_num}: Score: {ep_score}, Epsilon: {epsilon:.3f}")

# Plotting the learning progress
grapgh.plot(scores)
grapgh.xlabel("Episodes")
grapgh.ylabel("Score")
grapgh.title("Q-learning")
grapgh.legend()
grapgh.show()

env.close()
 